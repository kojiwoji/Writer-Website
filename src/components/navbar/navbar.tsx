import './navbar.css'

import { Menu, MenuButton, MenuItem, MenuItems } from '@headlessui/react'

export default function Navbar(){
	return <div className="bg-gray-900 w-2/6 mx-auto ">
		<div className="NavbarShape h-10 min-w-min mx-auto">
		    <div className="">
		      <div className="">
		        <div className="space-x-1">
		        	<a href="" className="text-gray-400 hover:text-white px-3 text-2xl font-semibold">Dashboard</a>
		        	<a href="" className="text-gray-400 hover:text-white px-3 text-2xl font-semibold">Scenarios</a>
		        	
		        	<Menu>
		        		<MenuButton className="text-gray-400 hover:text-white px-3 text-2xl font-semibold">
		        			Tools
		        		</MenuButton>
		    				<MenuItems
		    				anchor="bottom middle"
		    			  className="w-16 bg-gray-700 border-solid border rounded text-sm/6 text-white text-center"
		    				>
		    					<MenuItem className="hover:text-black">
		    						<a href="">
		    							<button>
		    								Item01
		    							</button>
		    						</a>
		    					</MenuItem >
		    					<MenuItem className="hover:text-black">
		    						<a href="">
		    							<button>
		    								Item02
		    							</button>
		    						</a>
		    					</MenuItem>
		    				</MenuItems>
		        	</Menu>
		        </div>
		      </div>
		    </div>
		</div>
	</div>;
}