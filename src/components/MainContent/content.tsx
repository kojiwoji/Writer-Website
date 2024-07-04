import React from 'react'

export default function MainContent({ Input }) {
	/* Note: The border is only used for debugging. Remove it when its not needed. */
	return <div className="border border-white w-6/12 my-4 mx-auto">
		<p className="text-white text-justify ">{Input}</p>
	</div>
}