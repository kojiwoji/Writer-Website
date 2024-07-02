import React from 'react'
import ReactDom from 'react-dom'

export default function ContentMain({ Input }){
	/* Note: The border is only used for debugging. Remove it when its not needed. */
	return <div className="border border-white w-6/12 my-4 mx-auto">
		<p className="text-white text-justify ">{ Input }</p>
	</div>
}